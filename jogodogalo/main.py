from tkinter import *

root = Tk()
root.title("Jogo da Galinha")


e = Entry(root, bg="gray", fg="white", borderwidth=5, width=35)
e.grid(row=0, column=0, columnspan=3, padx=10, pady=10)
e.insert(0, "Joga-mos")

def button_click(number):
    current = e.get()
    e.delete(0, END)
    e.insert(0, str(current) + str(number))

buttons = []
inserted = []

for i in range(10):
    buttons.append(Button(root, text=str(i), padx=50, pady=40, bg="gray", fg="white", command=lambda number=i: button_click(number)))

for i in range(1, 10):
    buttons[i].grid(row=int(3-i/3) + 1, column=(i-1) % 3)

root.mainloop()