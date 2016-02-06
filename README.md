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
To calculate the function to this truth table, we simply enter the
y-string after starting the program with ./lsa.
To the above truth table, we have to enter following:

./lsa -i
01120022

This input will lead to the function output.

y =  
(!x1 * x3) +  
(x2)  

The '*' stands for AND  
The '+' stands for OR  
The '!' stands for NOT  

Inputs are always named from x1 to xn

At the moment, the maximum amount of inputs is 16.  
It might work with more, but I'm not sure about that,
and really, where's the point in such a function?

---

To install the program, execute following commands:

mkdir obj  
make  

Then launch it with ./lsa and enter your y-string

For only minterms: use -i  
For only maxterms: use -a  
For both: use -b


