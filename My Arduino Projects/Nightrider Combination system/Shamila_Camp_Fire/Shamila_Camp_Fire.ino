
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {


    digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
        digitalWrite(11, HIGH);
          digitalWrite(9, HIGH);
            digitalWrite(8, HIGH);
              digitalWrite(7, HIGH);
                digitalWrite(5, HIGH);
                  digitalWrite(4, HIGH);
                    digitalWrite(3, HIGH);

    delay(3000);

    ///LED Tape wire................
    
  digitalWrite(13, LOW);   
  delay(1500);                      
  digitalWrite(13, HIGH);  
  delay(1500);
  

digitalWrite(13, LOW);   
  delay(1500);                      
  digitalWrite(13, HIGH);
  delay(1000);
    

  digitalWrite(13, LOW);   
  delay(1500);                      
  digitalWrite(13, HIGH); 
  delay(500);



  ////INTAKE 39 circuit...............


   digitalWrite(12, LOW);   
  delay(1000);                      
  digitalWrite(12, HIGH); 


  digitalWrite(11, LOW);   
  delay(1000);                      
  digitalWrite(11, HIGH); 


  digitalWrite(9, LOW);   
  delay(1000);                      
  digitalWrite(9, HIGH); 


  digitalWrite(8, LOW);   
  delay(1000);                      
  digitalWrite(8, HIGH); 

  digitalWrite(7, LOW);   
  delay(1000);                      
  digitalWrite(7, HIGH); 
  
  digitalWrite(5, LOW);   
  delay(1000);                      
  digitalWrite(5, HIGH); 

  digitalWrite(4, LOW);   
  delay(1000);                      
  digitalWrite(4, HIGH); 
  
  digitalWrite(3, LOW);   
  delay(1000);                      
  digitalWrite(3, HIGH); 




  delay(3000);


digitalWrite(13, LOW);
      digitalWrite(12, LOW);
        digitalWrite(11, LOW);
          digitalWrite(9, LOW);
            digitalWrite(8, LOW);
              digitalWrite(7, LOW);
                digitalWrite(5, LOW);
                  digitalWrite(4, LOW);
                    digitalWrite(3, LOW);


                    delay(3600000);

                    
digitalWrite(13, LOW);

                    
   
}
