int bin_to_int(String str, int length) //konversi string biner ke int
{
  int str_int=0;
  for(int i=0;i<length;i++){
    str_int=str_int<<1;
    str_int+=str[i]-'0';
  }
  return str_int;
}

void setup()
{
  Serial.begin(9600);	//set serial dengan 9600 bit per sekon
}

void loop()
{
  String str_A, str_B;	//string untuk menyimpan nilai biner
  int dec_a, dec_b;		//string untuk menyimpan nilai integer

  int length_a = 0;		//panjang string biner a dan b
  int length_b = 0;
  
  while(length_a==0){	//baca string A hingga string memiliki nilai bukan nol
    str_A = Serial.readString();
    length_a = str_A.length();
    if(length_a){
      Serial.print("A = ");
      Serial.println(str_A);
    }
  }
  while(length_b==0){	//baca string B hingga nilainya tidak nol
    str_B = Serial.readString();
    length_b = str_B.length();
    if(length_b){
      Serial.print("B = ");
      Serial.println(str_B);
    }
  }
  
  dec_a = bin_to_int(str_A,length_a);	//konversi a dan b ke integer
  dec_b = bin_to_int(str_B,length_b);
  int limit = bin_to_int("0111111111111111",16); //set batas max value, 16 bit
  
  if(dec_a==dec_b){				//jika a dan b sama, output SAMA
    Serial.println("SAMA");
 	Serial.println(dec_a);
 	Serial.println(dec_b);
  }
  else{							//jika tidak, output BEDA
    Serial.println("BEDA");
    while(dec_b<limit){			//increment nilai b
      dec_b+=1;
      if(dec_a==dec_b){			//jika sama, output SAMA dan nilainya
        Serial.println("SAMA");
 		Serial.println(dec_a);
 		Serial.println(dec_b);
        break;
      }
    }
    //jika hingga limit belum sama, output "tidak akan sama"
    if(dec_b==limit) Serial.println("B tidak akan sama dengan A");
  }
  
  delay(10000);	//berhentikan sesi sementara selama 10 detik
}
