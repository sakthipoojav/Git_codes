import serial
import csv

PORT = "COM4"
BAUD_RATE = 115200

filename = "imu_data.csv"

ser = serial.Serial(
    PORT,
    BAUD_RATE,
    timeout=1
)

print("Connected to ESP32-WROOM")
print("Saving data to:", filename)
print("Press Ctrl+C to stop.")
print()

with open(filename, "w", newline="") as csvfile:

    writer = csv.writer(csvfile)

    writer.writerow([
        "send_time_ms",
        "acc_x",
        "acc_y",
        "acc_z",
        "gyro_x",
        "gyro_y",
        "gyro_z"
    ])

    try:
        while True:

            line = ser.readline().decode(
                "utf-8",
                errors="ignore"
            ).strip()

            if line:

                print(line)

                values = line.split(",")

                if len(values) == 7:

                    writer.writerow(values)

                    csvfile.flush()

    except KeyboardInterrupt:

        print()
        print("Stopping data collection...")

ser.close()

print("Serial port closed.")
print("CSV file saved.")