public class Endereco {
    private String logradouro, cidade;
    private int numero;
    
    public Endereco(String logradouro, int numero, String cidade){
        this.logradouro = logradouro;
        this.numero = numero;
        this.cidade = cidade;
    }
    
    public Endereco(String endereco){
        String v[] = endereco.split(";");
        this.logradouro = v[0];
        this.numero = Integer.parseInt(v[1]);
        this.cidade = v[2];
    }
    
    public String string(){
        return this.logradouro + ";" + this.numero + ";" + this.cidade;
    }
    
    public String getLogradouro(){
        return this.logradouro;
    }
    
    public int getNumero(){
        return this.numero;
    }
    
    public String getCidade(){
        return this.cidade;
    }
    
    public void setLogradouro(String logradouro){
        this.logradouro = logradouro;
    }
    
    public void setNumero(int numero){
        this.numero = numero;
    }
    
    public void setCidade(String cidade){
        this.cidade = cidade;
    }
    
}
