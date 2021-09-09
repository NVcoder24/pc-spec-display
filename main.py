from serial import Serial
from time import sleep
import psutil
import GPUtil

port_path = "/dev/ttyUSB0"

port = Serial(port_path, 9600)

def get_cpu_temp():
    with open("/sys/class/thermal/thermal_zone0/temp") as file:
        temp = file.read()
        file.close()

        return str(int(float(temp) / 1000))

def get_ram_load():
    return str(int(psutil.virtual_memory().percent))

def get_gpu_temp():
    gpus = GPUtil.getGPUs()

    return str(int(gpus[0].temperature))

while True:
    data = f"{get_ram_load()},{get_cpu_temp()},{get_gpu_temp()};".encode("utf-8")

    port.write(data)

    print("wrote!")
    sleep(1)
