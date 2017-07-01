public class Carro extends Veiculo
{
	private int potencia;
	private int numeroCilindros;
	private int numeroOcupantes;
	private Tipo tipo;
	private double altura;
	private double largura;
	private double comprimento;
	
	public Carro(int Chassi, String marca, String modelo, int ano, double km, String comb, double p, Status s, int potencia, int cilindros, int ocupantes, Tipo t, double altura, double largura, double comprimento)
	{
		super(Chassi, marca, modelo, ano, km, comb, p, s);
		this.potencia = potencia;
		this.numeroCilindros = cilindros;
		this.numeroOcupantes = ocupantes;
		tipo = t;
		this.altura = altura;
		this.largura = largura;
		this.comprimento = comprimento;
	}
	
	public enum Tipo
	{
		UTILITARIO, PICKUP, SEDAN, HATCH, ESPORTIVO;
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
	
	public void setAltura(double a)
	{
		altura = a;
	}
	
	public void setLargura(double l)
	{
		largura = l;
	}
	
	public void setComprimento(double c)
	{
		comprimento = c;
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
	
	public double getAltura()
	{
		return altura;
	}
	
	public double getLargura()
	{
		return largura;
	}
	
	public double getComprimento()
	{
		return comprimento;
	}
}