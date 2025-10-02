# Kernel Handle Enumerator

A kernelmode handle enumerator for usermode processes.  <br>
Created due to a lack of existing resources when I searched for this myself, this driver allows enumeration of handles in <br>a process directly from kernelmode<br>


This driver walks the handle table of a target process in kernel mode and logs all handle entries. Offsets in this PoC are<br> for **Windows 10 22H2 x64**, but the concept(literally just walking from eprocess to a entry lol) works up to 24h2(to my knowledge).<br>
