import gmplot

# Function to read longitude and latitude from text file
def read_lon_lat_from_text(text_file):
    latitudes = []
    longitudes = []
    with open(text_file, 'r') as file:
        for line in file:
            # Check if the line contains a comma
            if ',' in line:
                # Split each line by comma
                lon, lat = line.strip().split(',')
                longitudes.append(float(lon))
                latitudes.append(float(lat))
            else:
                print("Skipping line:", line.strip())  # Print a message or handle the case where there's no comma
    return latitudes, longitudes

# Main function
def main():
    # Path to the text file
    text_file = "C:\\Users\\AGad\\Desktop\\next\\test.txt"

    # Read longitude and latitude from text file
    lat, long = read_lon_lat_from_text(text_file)

    gmap = gmplot.GoogleMapPlotter(30.064,31.278,14)
    gmap.scatter(lat,long,'#ff000',size=15)
    gmap.plot(lat,long,'red',edge_width=2.5)
    gmap.draw("map.html")

if __name__ == "__main__":
    main()