import java.util.*;

public class VendedorJr extends Vendedor {
    private int tempoTrabalho;
    private Gerente gerenteResponsavel;
    private String documentoGerente;

    public VendedorJr(String usuario, String senha, int tempoTrabalho, Gerente gerenteResponsavel, String nome, String rg, Data nasc, Data admissao, double salario) {
        super(usuario, senha, nome, rg, nasc, admissao, salario);
        this.tempoTrabalho = tempoTrabalho;
        this.gerenteResponsavel = gerenteResponsavel;
        this.documentoGerente = gerenteResponsavel.getDocumento();
    }
    
    public VendedorJr(String nome, String documento, Data nascimento, double renda, String usuario, String senha, Data admissao, int tempoTrabalho, String gerente){
        super(usuario, senha, nome, documento, nascimento, admissao, renda);
        this.tempoTrabalho = tempoTrabalho;
        this.gerenteResponsavel = null;
        this.documentoGerente = gerente;
        
    }

    public int getTempoTrabalho() {
        return tempoTrabalho;
    }

    public void setTempoTrabalho(int tempoTrabalho) {
        this.tempoTrabalho = tempoTrabalho;
    }

    public Gerente getGerenteResponsavel() {
        return gerenteResponsavel;
    }

    public void setGerenteResponsavel(Gerente gerenteResponsavel) {
        this.gerenteResponsavel = gerenteResponsavel;
    }
    
    public boolean atualizaGerente(List<Gerente> gerentes){
        
        for(Gerente gerente : gerentes)
            if(gerente.getDocumento().equals(this.documentoGerente)){
                this.gerenteResponsavel = gerente;
                return true;
            }
        
        return false;
    }
    
}
