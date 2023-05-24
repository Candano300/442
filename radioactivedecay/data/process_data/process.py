import os
import csv

# Define the input directory and output directory paths
input_directory = "./raw"
output_directory = "./processed"

# Define the multiplication factor
multiplier = 2  # Adjust this value as per your requirement

# Get a list of TSV files in the input directory
tsv_files = [file for file in os.listdir(input_directory)]

# Process each TSV file
for file_name in tsv_files:
    input_file_path = os.path.join(input_directory, file_name)
    output_file_path = os.path.join(output_directory, file_name)

    # Read the input TSV file and multiply the second column
    with open(input_file_path, "r") as file:
        reader = csv.reader(file, delimiter="\t")
        rows = list(reader)
        header = rows[0]  # Store the header row
        for row in rows[1:]:
            row[1] = str(float(row[1]) * multiplier)

    # Save the updated TSV file with multiplied values
    with open(output_file_path, "w", newline="") as file:
        writer = csv.writer(file, delimiter="\t")
        writer.writerow(header)  # Write the header row
        writer.writerows(rows[1:])  # Write the modified rows

    print(f"Processed file: {file_name}")

print("Multiplication completed successfully!")
