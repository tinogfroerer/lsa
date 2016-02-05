#lsa
##Calculate logic functions

This program calculates logic functions.  
It does this by using the Karnaugh map not as a two-dimensional construct
(which would allow only up to 5 inputs, afterwards it gets messy), but as an
n-dimensional construct.

Using the program:  
To constuct a logic function, you need a truth table:
x1, x2 and x3 are inputs. y is the output.

0 = LOGIC ZERO  
1 = LOGIC ONE  
2 = DONT CARE  

| x1| x2| x3|| y |   
| 0 | 0 | 0 || 0 |  
| 0 | 0 | 1 || 1 |  
| 0 | 1 | 0 || 1 |  
| 0 | 1 | 1 || 2 |  
| 1 | 0 | 0 || 0 |  
| 1 | 0 | 1 || 0 |  
| 1 | 1 | 0 || 2 |  
| 1 | 1 | 1 || 2 |  

The information of x1..x3 is redundant, we will always write truth tables like this.
To calculate the function to this truth table, we simply enter the string of the output:

./lsa  
01120022

This input will lead to the function output.

NOTE: At the moment, it isn't outputting anything, but that'll be my next commit.

---

To make the program, execute following commands:

mkdir obj
make

