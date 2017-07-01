public class Funcionario extends Pessoa{
    
    private Data admissao;
    
    private String usuario, senha;
   
    public Funcionario(String usuario, String senha, String nome, String documento, Data admissao, Data nasc, double salario) {
        super(nome, documento, nasc, salario);
        this.usuario = usuario;
        this.senha = senha;
        this.admissao = admissao;
    }
    
    public Data getAdmissao() {
        return admissao;
    }

    public void setAdmissao(Data admissao) {
        this.admissao = admissao;
    }

    public double getSalario() {
        return renda;
    }

    public void setSalario(double salario) {
        this.renda = salario;
    }
    
    public String getUsuario(){
        return this.usuario;
    }
    
    public String getSenha(){
        return this.senha;
    }
    
    public void setUsuario(String usuario){
        this.usuario = usuario;
    }
    
    public void setSenha(String senha){
        this.senha = senha;
    }
    
}
