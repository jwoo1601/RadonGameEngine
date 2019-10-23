# Radon Project Manager
# Version: 0.1.0

import tkinter

root = tkinter.Tk()
root.title('Radon Project Manager')
root.maxsize(400, 400)

def newButton(text:str, callback):
    return tkinter.Button(mainWindow, text=text, command=callback, relief='groove', padx=3, pady=3)

def newTextbox(callback):
    return tkinter.Entry(mainWindow, exportselection=0, state='disabled')

########################################################################################################
def onTbNamespace():
    pass

def onBtnSelectNamespace():
    pass

tbNamespace = newTextbox(onTbNamespace)
btnSelectNamespace = newButton('select namespace', onBtnSelectNamespace)

tbNamespace.pack(side='left')
btnSelectNamespace.pack(side='right')
root.mainloop()