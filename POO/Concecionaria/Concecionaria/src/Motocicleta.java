public class Motocicleta extends Veiculo
{
	private int cilindradas;
	private Tipo tipo;
	
	public Motocicleta(int Chassi, String marca, String modelo, int ano, double km, String comb, double p, Status s, int cilindradas, Tipo t)
	{
		super(Chassi, marca, modelo, ano, km, comb, p, s);
		this.cilindradas = cilindradas;
		tipo = t;
	}
	
	public enum Tipo
	{
		TRAIL, STREET, ESPORTIVA, CUSTOM;
	}
	
	public void setCilindradas(int c)
	{
		cilindradas = c;
	}
	
	public void setTipo(Tipo t)
	{
		tipo = t;
	}
	
	public int getCilindradas()
	{
		return cilindradas;
	}
	
	public Tipo getTipo()
	{
		return tipo;
	}
}