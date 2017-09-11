public class VendedorS extends Vendedor{
    private int anosTrabalho;
    private int ultimoAumento;

    public VendedorS(String usuario, String senha, int anosTrabalho, String nome, String rg, Data nasc, Data admissao, double salario, int ultimoAumento) {
        super(usuario, senha, nome, rg, nasc, admissao, salario);
        this.anosTrabalho = anosTrabalho;
        this.ultimoAumento = ultimoAumento;
    }

    public int getAnosTrabalho() {
        return anosTrabalho;
    }

    public void setAnosTrabalho(int t) {
        anosTrabalho = t;
    }
    
    
    
    public void darAumento(){
        this.setRenda(this.getRenda() * 1.015);
    }

    public int getUltimoAumento() {
        return ultimoAumento;
    }

    public void setUltimoAumento(int ultimoAumento) {
        this.ultimoAumento = ultimoAumento;
    }
    
    
}
