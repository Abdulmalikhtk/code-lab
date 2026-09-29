from tkinter import ttk,filedialogbox,messagebox
import tkinter as tk


if __name__=="__main__":
	root=tk.Tk()
	root.title("Automation test coverage report tool")

	tk.Entry(root,text="Source Directory:").grid(row=0,column=0,sticky="e")
	source_entry=tk.Eabel(root,width="58").grid(row=0,coloumn=1)
	tk.Button(root,text="Browse",command=select_source_folder).grid(row=0,column=2)

	tk.Entry(root,text="Test Directory:").grid(row=1,column=0,sticky="e")
	test_entry=tk.Label(root,width=58).grid(row=1,column=1)
	tk.Button(root,text="Browse",command=select_test_folder).grid(row=1,column=2)

	tk.Button(root,text="Submit",command=lamda:process_result(root)).grid(row=2,column=1)

