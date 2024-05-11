import pandas as pd
import os

def load_and_preprocess() -> tuple[pd.DataFrame, list[pd.DataFrame]]:
    well_info = pd.read_csv('well-loc.tsv', sep='\t')

    # Path to the sensor data directory
    sensor_data_path = 'sensor-data'

    # List all TSV files in the directory
    sensor_data_files = [f for f in os.listdir(sensor_data_path) if f.endswith('.tsv')]

    # Sort the sensor_data_files list
    sensor_data_files.sort(key= lambda x: int(x.split('.')[0]))

    # Load and concatenate all sensor data files into one DataFrame
    sensor_data_list = [pd.read_csv(os.path.join(sensor_data_path, file), sep='\t',
                                    na_values="-9999") for file in sensor_data_files]

    # Remove the data point with NaN value
    well_info = well_info.dropna()
    for sensor_data in sensor_data_list:
        sensor_data.dropna(inplace=True)

    # Reset the index of the well_loc DataFrame to Well, X, Y
    well_info.rename(columns={'井': 'Well'}, inplace=True)

    # Reset the index of the sensor data DataFrame to Depth, Porosity, Hydrate Saturation
    for idx, _ in enumerate(sensor_data_list):
        sensor_data_list[idx].columns = ['Depth', 'Porosity', 'Hydrate Saturation']


    from sklearn.preprocessing import MinMaxScaler

    # Normalize the sensor data
    scaler = MinMaxScaler()
    for idx, sensor_data in enumerate(sensor_data_list):
        sensor_data[['Porosity', 'Hydrate Saturation']] = scaler.fit_transform(sensor_data[['Porosity', 'Hydrate Saturation']])
        
        
    def estimate_resource(sensor_data: pd.Series) -> float:
        """Estimate the resource at a given location based on sensor data"""
        # Get the Porosity and the Hydrate saturation
        porosity = sensor_data['Porosity']
        hydrate_saturation = sensor_data['Hydrate Saturation']

        valid_volume = 1 # Assume the valid volume is 1 cubic meter
        factor = 155 # Assume the factor is 155

        # Calculate the resource estimate
        return valid_volume * porosity * hydrate_saturation * factor


    # Calculate the resource estimate for each sensor data in each depth
    for idx, sensor_data in enumerate(sensor_data_list):
        sensor_data_list[idx]['Estimated Resources'] = sensor_data.apply(estimate_resource, axis=1)

    sensor_data_list[0]

    resource_sums = [df['Estimated Resources'].sum() for df in sensor_data_list]
    well_info['Total Resources'] = resource_sums
    
    return well_info, sensor_data_list