public class Dim {
   
    private double altura, largura, comprimento;
    
    public Dim(double altura, double largura, double comprimento){
        this.altura = altura;
        this.largura = largura;
        this.comprimento = comprimento;
    }
    
    public Dim(String entrada){
        String v[] = entrada.split(";");
    }
    
    public String string(){
        String r = "";
        
        r = r + Double.toString(altura) + ";"
                + Double.toString(largura) + ";"
                + Double.toString(comprimento);
        
        return r;
    }
    
    public double getAltura(){
        return this.altura;
    }
    
    public double getLargura(){
        return this.largura;
    }
    
    public double getComprimento(){
        return this.comprimento;
    }
    
    public void setAltura(double altura){
        this.altura = altura;
    }
    
    public void setLargura(double largura){
        this.largura = largura;
    }
    
    public void setComprimento(double comprimento){
        this.comprimento = comprimento;
    }
    
}
