```mermaid
    graph LR
    A(PC_USB1) --- C(USB2TTL)
    C --- E((RX)) <--> H((TX)) --- D(CH9329) 
    C --- F((TX)) <--> G((RX)) --- D(CH9329) --- B(PC_USB2)
```
![screenshot](doc/screenshot.jpg)