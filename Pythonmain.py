import subprocess
import os
import matplotlib.pyplot as plt

def get_valid_number(prompt_text, must_be_integer):
    while True:
        user_input = input(prompt_text)
        try:
            if must_be_integer:
                value = int(user_input)
                if value < 0:
                    print("Error: Please enter a positive number.")
                    continue
                return str(value)
            else:
                value = float(user_input)
                if value < 0:
                     print("Error: Please enter a positive number.")
                     continue
                return str(value)
        except ValueError:
            if must_be_integer:
                print("Error: Please enter a whole number (no decimals or letters).")
            else:
                print("Error: Please enter a valid number (e.g., 25.5).")
                
def get_valid_name():
    while True:
        name = input("Enter Fluid Name (letters only): ")
        if name.replace(" ", "").isalpha():
            return name
        else:
            print("Error: Invalid name. Please do not use numbers or symbols.")
            
flow_rate = get_valid_number("Enter Flow Rate(m3):",must_be_integer=False)
length = get_valid_number("Enter Pipe Length (m):",must_be_integer=False)
diameter = get_valid_number("Enter Pipe Diameter (m):",must_be_integer=False)
fluid_name = get_valid_name()
temperature = get_valid_number("Enter Temperature (C): ",must_be_integer=False)

with open("user_input.txt", "w") as f:
        f.write(flow_rate + "\n")
        f.write(length + "\n")
        f.write(diameter + "\n")
        f.write(fluid_name + "\n") 
        f.write(temperature + "\n")

elbow_90 = get_valid_number("Enter Number of 90 ° elbow:",must_be_integer=True)
elbow_45 = get_valid_number("Enter Number of 45 ° elbow:",must_be_integer=True)
fogv = get_valid_number("Enter Number of Fully Open Gate valve:",must_be_integer=True)
bft = get_valid_number("Enter Number of branch flow tee:",must_be_integer=True)
tft = get_valid_number("Enter Number of through flow tee:",must_be_integer=True)
scv = get_valid_number("Enter Number swing check valve:",must_be_integer=True)

with open("user_fittings.txt", "w") as f:
        f.write(elbow_90 + "\n")
        f.write(elbow_45 + "\n")
        f.write(fogv + "\n")
        f.write(bft + "\n") 
        f.write(tft + "\n")
        f.write(scv + "\n")
