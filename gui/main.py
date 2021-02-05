from tkinter import *

root = Tk()
root.title("Calculadora do Aço")

e = Entry(root, bg="gray", fg="white", borderwidth=5, width=35)
e.grid(row=0, column=0, columnspan=3, padx=10, pady=10)
e.insert(0, "Calcula-mos")

def button_click(number):
    current = e.get()
    e.delete(0, END)
    e.insert(0, str(current) + str(number))

def button_add():
    inserted.append(int(e.get()))
    e.delete(0, END)
    return

def button_equal():
    inserted.append(int(e.get()))
    e.delete(0, END)
    result = 0
    for i in range(len(inserted)):
        result += inserted.pop()

    e.insert(0, result)

def button_clear():
    e.delete(0, END)
    return

buttons = []
inserted = []

for i in range(10):
    buttons.append(Button(root, text=str(i), padx=40, pady=20, bg="gray", fg="white", command=lambda number=i: button_click(number)))

buttons.append(Button(root, text="+", padx=39, pady=20, bg="gray", fg="white", command=button_add))
buttons.append(Button(root, text="=", padx=91, pady=20, bg="gray", fg="white", command=button_equal))
buttons.append(Button(root, text="Clear", padx=29, pady=20, bg="gray", fg="white", command=button_clear))

for i in range(1, 10):
    buttons[i].grid(row=int(3-i/3) + 1, column=(i-1)%3)
buttons[0].grid(row=4, column=1)
buttons[10].grid(row=4, column=0)
buttons[11].grid(row=5, column=0, columnspan=3)
buttons[12].grid(row=4, column=2)


root.mainloop()