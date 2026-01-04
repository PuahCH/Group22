import subprocess
import os
import matplotlib.pyplot as plt
import sys
import tkinter as tk
from tkinter import messagebox

def get_all_simulation_inputs():
    window = tk.Tk()
    window.title("Pipe Simulation Dashboard")
    window.geometry("500x700") 
    
    fluid_var = tk.StringVar(value="Water") 
    temp_var = tk.DoubleVar(value=20.0)
    
    def submit():
        try:
            flow = float(entry_flow.get())
            length = float(entry_length.get())
            diam = float(entry_diam.get())

            e90 = int(entry_e90.get() or 0)
            e45 = int(entry_e45.get() or 0)
            gate = int(entry_gate.get() or 0)
            t_branch = int(entry_t_branch.get() or 0)
            t_thru = int(entry_t_thru.get() or 0)
            swing = int(entry_swing.get() or 0)
            
            if any(x < 0 for x in [flow, length, diam, e90, e45, gate, t_branch, t_thru, swing]):
                messagebox.showerror("Error", "Values cannot be negative.")
                return

            window.user_data = {
                "fluid": fluid_var.get(),
                "temp": str(int(temp_var.get())),
                "flow": str(flow),
                "length": str(length),
                "diam": str(diam),
                "elbow90": str(e90),
                "elbow45": str(e45),
                "gatevalve": str(gate),
                "teebranch": str(t_branch),
                "teethru": str(t_thru),
                "swingcheck": str(swing)
            }
            window.destroy()
            
        except ValueError:
            messagebox.showerror("Error", "Please check your inputs.\nDimensions must be numbers.\nFittings must be whole numbers (integers).")

    tk.Label(window, text="1. Select Fluid", font=("Arial", 10, "bold")).pack(pady=(10, 5))
    f_frame = tk.Frame(window)
    f_frame.pack()
    frame_fluid = tk.Frame(window)
    frame_fluid.pack()
    tk.Radiobutton(frame_fluid, text="Water", variable=fluid_var, value="Water").pack(side="left", padx=10)
    tk.Radiobutton(frame_fluid, text="Oil", variable=fluid_var, value="Oil").pack(side="left", padx=10)
    tk.Radiobutton(frame_fluid, text="Air", variable=fluid_var, value="Air").pack(side="left", padx=10)
    tk.Frame(window, height=1, bg="lightgrey").pack(fill="x", pady=5, padx=20)

    tk.Label(window, text="2. Temperature (C)", font=("Arial", 10, "bold")).pack(pady=5)
    tk.Scale(window, variable=temp_var, from_=0, to=100, resolution=5, orient="horizontal", length=300).pack()

    tk.Frame(window, height=1, bg="lightgrey").pack(fill="x", pady=5, padx=20)

    tk.Label(window, text="3. System Dimensions", font=("Arial", 10, "bold")).pack(pady=5)
    d_frame = tk.Frame(window)
    d_frame.pack()
    
    def make_entry(parent, label, row, col, default):
        tk.Label(parent, text=label).grid(row=row, column=col, sticky="e", padx=5, pady=3)
        e = tk.Entry(parent, width=10)
        e.grid(row=row, column=col+1, padx=5, pady=3)
        e.insert(0, default)
        return e

    entry_flow = make_entry(d_frame, "Flow (m3/s):", 0, 0, "0.005")
    entry_length = make_entry(d_frame, "Length (m):", 1, 0, "50.0")
    entry_diam = make_entry(d_frame, "Diameter (m):", 2, 0, "0.05")

    tk.Frame(window, height=1, bg="lightgrey").pack(fill="x", pady=10, padx=20)

    tk.Label(window, text="4. Fittings Count (Integers)", font=("Arial", 10, "bold")).pack(pady=5)
    fit_frame = tk.Frame(window)
    fit_frame.pack()

    entry_e90 = make_entry(fit_frame, "90° Elbows:", 0, 0, "0")
    entry_e45 = make_entry(fit_frame, "45° Elbows:", 1, 0, "0")
    entry_gate = make_entry(fit_frame, "Gate Valve:", 2, 0, "0")

    entry_t_branch = make_entry(fit_frame, "Tee (Branch):", 0, 2, "0")
    entry_t_thru = make_entry(fit_frame, "Tee (Thru):", 1, 2, "0")
    entry_swing = make_entry(fit_frame, "Swing Check:", 2, 2, "0")

    tk.Button(window, text="RUN SIMULATION", command=submit, bg="green", fg="white", font=("bold"), height=2, width=20).pack(pady=20)

    window.mainloop()
    return getattr(window, "user_data", None)

data = get_all_simulation_inputs()

if data:
    with open("user_input.txt", "w") as f:
        f.write(data["flow"] + "\n")
        f.write(data["length"] + "\n")
        f.write(data["diam"] + "\n")
        f.write(data["fluid"] + "\n")
        f.write(data["temp"] + "\n")
        
    with open("user_fittings.txt", "w") as f:
        f.write(data["elbow90"] + "\n")
        f.write(data["elbow45"] + "\n")
        f.write(data["gatevalve"] + "\n")
        f.write(data["teebranch"] + "\n")
        f.write(data["teethru"] + "\n")
        f.write(data["swingcheck"] + "\n")

    if os.name == 'nt': 
        exe_path = "pipe_simulation.exe" 
        startup_info = subprocess.STARTUPINFO()
        startup_info.dwFlags |= subprocess.STARTF_USESHOWWINDOW
        startup_info.wShowWindow = subprocess.SW_HIDE
    else:
        exe_path = "./pipe_simulation"
        startup_info = None

    if not os.path.exists(exe_path):
        messagebox.showerror("Error", f"Could not find {exe_path}")
        sys.exit(1)

    try:
        run_cmd = [exe_path]
        result = subprocess.run(run_cmd, capture_output=True, text=True, startupinfo=startup_info)
        
        if result.returncode != 0:
            messagebox.showerror("C++ Error", result.stderr)
            sys.exit(1)
            
    except Exception as e:
        messagebox.showerror("Execution Error", str(e))
        sys.exit(1)

    results_file = "final_recommendation.txt"

    if os.path.exists(results_file):
        try:
            with open(results_file, "r") as f:
                lines = [line.strip() for line in f.readlines() if line.strip()]
            
            if len(lines) >= 6:
                prices = [float(lines[0]), float(lines[1]), float(lines[2])]
                names = [lines[3], lines[4], lines[5]]
                
                plt.figure(figsize=(10, 6))
                
                bars = plt.bar(names, prices, color=['#4CAF50', '#2196F3', '#FF9800'])
                
                fluid_name = data["fluid"] 
                plt.title(f"Cost Comparison for {fluid_name} System", fontsize=14, fontweight='bold')
                
                plt.ylabel("Total Cost (RM)", fontsize=12)
                plt.grid(axis='y', linestyle='--', alpha=0.7)
                
                for bar in bars:
                    height = bar.get_height()
                    plt.text(bar.get_x() + bar.get_width()/2.0, height, 
                             f'RM{height:.2f}', 
                             ha='center', va='bottom', fontsize=11, fontweight='bold')
                
                plt.show()
                
            else:
                messagebox.showerror("Data Error", "Result file is missing data lines!")
                
        except Exception as e:
            messagebox.showerror("Plot Error", f"Could not draw chart: {e}")
    else:
        messagebox.showwarning("Result Error", "No results file found.")

else:
    pass

try:
    os.remove("user_input.txt")
    os.remove("user_fittings.txt")
    os.remove("final_recommendation.txt")
    os.remove("physics_results.txt")
    os.remove("clean_data.txt")
    os.remove("total_loss.txt")
except:
    pass 
