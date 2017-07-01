public class VendedorS extends Vendedor{
    private int anosTrabalho;

    public VendedorS(String usuario, String senha, int anosTrabalho, String nome, String rg, Data nasc, Data admissao, double salario) {
        super(usuario, senha, nome, rg, nasc, admissao, salario);
        this.anosTrabalho = anosTrabalho;
    }

    public int getAnosTrabalho() {
        return anosTrabalho;
    }

    public void setAnosTrabalho(int t) {
        anosTrabalho = t;
    }
    
    /*public float darAumento(){
        
    }*/
}
