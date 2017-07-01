import java.util.*;
import java.io.*;
import java.text.*;

public class Data
{	
        private int dia, mes, ano;
        
        public Data(int dia, int mes, int ano){
            this.dia = dia;
            this.mes = mes;
            this.ano = ano;
        }
        
        public Data(String d){
            String data[] = d.split("/");
            this.dia = Integer.parseInt(data[0]);
            this.mes = Integer.parseInt(data[1]);
            this.ano = Integer.parseInt(data[2]);   
        }
        
        public Data(){
            this.dia = 0;
            this.mes = 0;
            this.ano = 0;
        }
        
        public int getDia(){
            return this.dia;
        }
        
        public int getMes(){
            return this.mes;
        }
        
        public int getAno(){
            return this.ano;
        }
        
        public void setDia(int dia){
            this.dia = dia;
        }
        
        public void setMes(int mes){
            this.mes = mes;
        }
        
        public void setAno(int ano){
            this.ano = ano;
        }
		
	public void setAtctualData(){
		Calendar calendar = Calendar.getInstance();
		
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		
		String data[] = dateFormat.format(calendar.getTime()).split("/");
                
                this.dia = Integer.parseInt(data[0]);
                this.mes = Integer.parseInt(data[1]);
                this.ano = Integer.parseInt(data[2]);
               
	}
        
        public String string(){            
            return this.dia + "/" + this.mes + "/" + this.ano;
        }
}