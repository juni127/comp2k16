public class Cliente extends Pessoa {
    private Endereco endereco;
    private int dependentes;
    
    public Cliente(String nome, String rg, Data nasc, double renda, Endereco endereco, int dependentes){
        super(nome,rg,nasc,renda);
        this.endereco=endereco;
        this.dependentes=dependentes;
    }

    public Endereco getEndereco() {
        return endereco;
    }

    public void setEndereco(Endereco endereco) {
        this.endereco = endereco;
    }

    public int getDependentes() {
        return dependentes;
    }

    public void setDepend(int d) {
        dependentes = d;
    }
    
    
}
