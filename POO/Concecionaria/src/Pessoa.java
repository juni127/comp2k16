public abstract class Pessoa {
    protected String nome;
    protected String documento;
    protected Data nasc;
    protected double renda;

    public String getNome() {
        return nome;
    }

    public Pessoa(String nome, String documento, Data nasc, double renda) {
        this.nome = nome;
        this.documento = documento;
        this.nasc = nasc;
        this.renda = renda;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getDocumento() {
        return documento;
    }

    public void setDocumento(String documento) {
        this.documento = documento;
    }

    public Data getNasc() {
        return nasc;
    }

    public void setNasc(Data nasc) {
        this.nasc = nasc;
    }

    public double getRenda() {
        return renda;
    }

    public void setRenda(double renda) {
        this.renda = renda;
    }
    
    
}
