# BTree-calculator
It's an app that calculates the value of a mathematical expression and views the syntax binary tree built by parser. Allowed operators: *,/,^,+,- and braces.
Example:
input:
2+5+11*(20*15*14)+20*2*(3+5+2)
output:<br>
 = 46607<br>
 <pre style="background: white!">
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
