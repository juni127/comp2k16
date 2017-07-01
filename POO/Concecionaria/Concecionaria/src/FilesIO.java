
import java.io.*;
import java.util.*;

public class FilesIO<T> {
    
    private File arquivo;
    
    public FilesIO(String path){
        try{
            
            arquivo = new File(path);
            if(!arquivo.exists())
                arquivo.createNewFile();
        
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    
    public boolean write(List<T> data){
        boolean output = false;
        
        try{
            FileWriter fileWriter = new FileWriter(arquivo);
        
            if(data.isEmpty())
                return output;
            
            //Escreve o cabeçalho do arquivo
            if(data.get(0) instanceof Gerente)
                fileWriter.write("GERENTES");
            else if(data.get(0) instanceof VendedorS)
                fileWriter.write("SENIORS");
            else if(data.get(0) instanceof VendedorJr)
                fileWriter.write("JUNIORS");
            else if(data.get(0) instanceof Cliente)
                fileWriter.write("CLIENTES");
            else if(data.get(0) instanceof Carro)
                fileWriter.write("CARROS");
            else if(data.get(0) instanceof Motocicleta)
                fileWriter.write("MOTOCICLETAS");
            else if(data.get(0) instanceof Prazo)
                fileWriter.write("PRAZO");
            else if(data.get(0) instanceof Vista)
                fileWriter.write("VISTA");
            
            //Escreve os dados no arquivo
            for(T d : data){
                if(d instanceof Gerente){
                    Gerente gerente = (Gerente)d;
                    fileWriter.write(gerente.getUsuario());
                    fileWriter.write(gerente.getSenha());
                }
            }
            
            //Termina o arquivo
            fileWriter.close();
            output = true;
            
        }catch(IOException e){
            e.printStackTrace();
        }
        
        return output;
    }
    
    public List<T> read(){
        List<T> output = new ArrayList<T>();
        
        try{
        
            BufferedReader bReader = new BufferedReader(new FileReader(arquivo));
        
            int type = 0;
            
            switch(bReader.readLine()){
                case "GERENTES":
                    type = 0;
                    break;
            }
            
            String line;
            while((line = bReader.readLine()) != null){
                switch(type){
                    //Gerentes
                    case 0:
                        String senha;
                        senha = bReader.readLine();
                        output.add((T) new Gerente(line, senha));
                        break;
                }
            }
        
        }catch(IOException e){
            e.printStackTrace();
        }
        
        return output;
    }
    
}
