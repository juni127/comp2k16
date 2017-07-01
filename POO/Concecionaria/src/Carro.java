public class Carro extends Veiculo
{
	private int potencia;
	private int numeroCilindros;
	private int numeroOcupantes;
	private Tipo tipo;
	private Dim dimensoes;
	
	public Carro(int Chassi, String marca, String modelo, int ano, double km, String comb, double p, Status s, int potencia, int cilindros, int ocupantes, Tipo t, Dim dimensoes)
	{
		super(Chassi, marca, modelo, ano, km, comb, p, s);
		this.potencia = potencia;
		this.numeroCilindros = cilindros;
		this.numeroOcupantes = ocupantes;
		this.tipo = t;
                this.dimensoes = dimensoes;
	}
	
	public enum Tipo
	{
		UTILITARIO, PICKUP, SEDAN, HATCH, ESPORTIVO;
	}
        
        public static Tipo parseTipo(String s){
            switch(s){
                case "UTILITARIO":
                    return Tipo.UTILITARIO;
                case "PICKUP":
                    return Tipo.PICKUP;
                case "SEDAN":
                    return Tipo.SEDAN;
                case "HATCH":
                    return Tipo.HATCH;
                default:
                    return Tipo.ESPORTIVO;
            }
        }
	
	public void setPotencia(int p)
	{
		potencia = p;
	}
	
	public void setCilindros(int c)
	{
		numeroCilindros = c;
	}
	
	public void setOcupantes(int o)
	{
		numeroOcupantes = o;
	}
	
	public void setTipo(Tipo t)
	{
		tipo = t;
	}
	
	public void setDimensoes(Dim d)
	{
		this.dimensoes = d;
	}
	
	public int getPotencia()
	{
		return potencia;
	}
	
	public int getCilindros()
	{
		return numeroCilindros;
	}
	
	public int getOcupantes()
	{
		return numeroOcupantes;
	}
	
	public Tipo getTipo()
	{
		return tipo;
	}
	
	public Dim getDimensoes()
	{
		return dimensoes;
	}
}