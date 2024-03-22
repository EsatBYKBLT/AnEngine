#shader vertex
#version 330 core                           
layout (location = 0) in vec3 aPos;        
layout (location = 1) in vec3 aNormal;      
layout (location = 2) in vec4 aColor;   
layout (location = 3) in vec2 aTexCoord;   

out vec2 TexCoord;  
out vec4 vColor;  

uniform float time;

uniform mat4 u_MVP; 
 
                                                                                                
void main() {                                   
   TexCoord = vec2(aTexCoord.x, aTexCoord.y);
   vColor = aColor;
   gl_Position = u_MVP * vec4(aPos, 1.0);
}                                               





#shader fragment
#version 330 core    

in vec2 TexCoord;      
in vec4 vColor;         

out vec4 FragColor;       
uniform sampler2D texture1; 
                                                  
void main() {                                     
   //FragColor = vColor;   
   FragColor = texture(texture1, TexCoord);    
}                                                 