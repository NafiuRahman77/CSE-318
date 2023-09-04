# Set the terminal and output file
gnuplot <<EOF
set terminal pngcairo size 800,600 enhanced font 'Verdana,12'
set output 'Partition_vs_Mean_Accuracy.png'

# Set plot title and labels for axes
set title "Partition vs Mean Accuracy"
set xlabel "Partition"
set ylabel "Mean Accuracy"

# Define the data file and specify the columns to be used
datafile = "report.txt"  # Replace with your actual data file name

# Plot the data with lines
plot datafile using 1:2 with lines title "Mean Accuracy"
EOF


# Set the terminal and output file
gnuplot <<EOF
set terminal pngcairo size 800,600 enhanced font 'Verdana,12'
set output 'Partition_vs_Standard_Deviation.png'

# Set plot title and labels for axes
set title "Partition vs Standard Deviation"
set xlabel "Partition"
set ylabel "Standard Deviation"

# Define the data file and specify the columns to be used
datafile = "report.txt"  # Replace with your actual data file name

# Plot the data with lines
plot datafile using 1:3 with lines title "Standard Deviation"
EOF
     

