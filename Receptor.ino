
# define getLength(arr) ( sizeof(arr) / sizeof(arr[0]) )

int detector = 8;
int dotTime  = 150;
int dashTime = dotTime * 2;
int asterixTime = dotTime * 3;
int slashTime  = dotTime * 4;
 

String tableAlphabet[37] = {
  "A", "B", "C", "D", "E", "F", "G", "H",
  "I", "J", "K", "L", "M", "N", "O", "P",
  "Q", "R", "S", "T", "U", "V", "W", "X",
  "Y", "Z", "0," "1", "2", "3", "4", "5",
  "6", "7", "8", "9"
};
String tableMorse[37] = {
  // A    B       C       D     E     F     G       H
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
  // I    J       K     L       M     N     O       P
  "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
  // Q     R      S     T     U     V       W       X
  "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
  // Y      Z       0        1        2         3       4
  "-.--", "--..", ".----", "..---", "...--", "....-", ".....",
  // 5        6       7         8        9   
  "-....", "--...", "---..", "----.", "-----"
};

String decoded = "";
String letter = "";



void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  
  int val = digitalRead( detector );
  while ( val )
  {
    val = digitalRead( detector );
  }


  while ( !val ) 
  {
    int firstTime = millis();
    while ( !val )
    {
      val = digitalRead( detector );
    }
      
    int secondTime = millis();
    int delta = secondTime - firstTime;
    
    if ( delta > dotTime - 40 && delta < dotTime + 40 ) 
    {
      letter.concat( "." );
    } else if ( delta >  dashTime - 40 && delta <  dashTime + 40 ) 
    {
      letter.concat( "-" );
    } else if ( delta > asterixTime - 40 && delta < asterixTime + 40 )
    {
      // letter is finished
      for ( int i = 0; i < (int) getLength( tableAlphabet ); i++ )
      {
        if ( tableMorse[ i ] == letter ) 
        {
          String c = tableAlphabet[ i ];
          decoded.concat( c ); 
          letter = "";
          return;
        }
      }
    } else if ( delta > slashTime - 40 && delta < slashTime + 40 ) 
    {
      decoded.concat( " " );
    }
    
    Serial.print( "\n" );
    Serial.print( decoded );
  }
}

