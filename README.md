# BTree-calculator
It's an app that calculates the value of a mathematical expression and views the syntax binary tree built by parser. Allowed operators: \*,/,^,+,- and braces.
Example:<br>
input:<br>
<b>2+5+11*(20*15*14)+20*2*(3+5+2)</b><br>
output:<br>
 <pre>
 = 46607
                 (+)                       
                 / \                       
                /   \                      
               /     \                     
              /       \                    
             /         \                   
            /           \                  
           /             \                 
          /               \                
         /                 \               
       (+)                 (*)             
       / \                 / \             
      /   \               /   \            
     /     \             20   (*)          
    /       \                 / \          
  (+)       (*)              /   \         
  / \       / \             2    (+)       
 /   \     /   \                 / \       
2     5   11   (*)              /   \      
               / \            (+)    2     
              /   \           / \          
             20   (*)        /   \         
                  / \       3     5        
                 /   \                     
                15    14         
</pre>
