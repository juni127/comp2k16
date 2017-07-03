public abstract class Veiculo
{
	private int nChassi;
	private String marca;
	private String modelo;
	private int ano;
	private double quilometragem;
	private String combustivel;
	private double peso;
	private Status status;
        private int id;
	
	public Veiculo(int Chassi, String marca, String modelo, int ano, double km, String comb, double p, Status s)
	{
		nChassi = Chassi;
		this.marca = marca;
		this.modelo = modelo;
		this.ano = ano;
		quilometragem = km;
		combustivel = comb;
		peso = p;
		status = s;
	}
	
	public enum Status
	{
		VENDIDO, A_VENDA;
	}
        
        public static Status parseStatus(String s){
            switch(s){
                case "VENDIDO":
                    return Status.VENDIDO;
                default:
                    return Status.A_VENDA;
            }
        }
	
	public void setChassi(int chassi)
	{
		nChassi = chassi;
	}
	
	public void setMarca(String m)
	{
		marca = m;
	}
	
	public void setModelo(String m)
	{
		modelo = m;
	}
	
	public void setAno(int ano)
	{
		this.ano = ano;
	}
	
	public void setKm(double km)
	{
		quilometragem = km;
	}
	
	public void setComb(String c)
	{
		combustivel = c;
	}
	
	public void setPeso(double p)
	{
		peso = p;
	}
	
	public void setStatus(Status s)
	{
		status = s;
	}
	
	public int getChassi()
	{
		return nChassi;
	}
	
	public String getMarca()
	{
		return marca;
	}
	
	public String getModelo()
	{
		return modelo;
	}
	
	public int getAno()
	{
		return ano;
	}
	
	public double getKm()
	{
		return quilometragem;
	}
	
	public String getComb()
	{
		return combustivel;
	}
	
	public double getPeso()
	{
		return peso;
	}
	
	public Status getStatus()
	{
		return status;
	}
}