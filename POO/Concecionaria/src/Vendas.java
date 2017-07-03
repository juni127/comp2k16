
import java.util.List;

public abstract class Vendas {
    protected int id;
    protected Funcionario vendedor;
    protected Cliente cliente;
    protected Veiculo veiculo;
    protected double valor;
    protected Data data;
    protected double desconto;
    
    protected String vendedorDoc;
    protected String clienteDoc;

    public Vendas(int id, Funcionario vendedor, Cliente cliente, Veiculo veiculo, double valor, Data data, double desconto) {
        this.id = id;
        this.vendedor = vendedor;
        this.cliente = cliente;
        this.veiculo = veiculo;
        this.valor = valor;
        this.data = data;
        this.desconto = desconto;
        this.vendedorDoc = "";
        this.clienteDoc = "";
    }
    
    public Vendas(int id, Veiculo veiculo, double valor, Data data, double desconto, String vendedorDoc, String clienteDoc) {
        this.id = id;
        this.vendedor = null;
        this.cliente = null;
        this.veiculo = veiculo;
        this.valor = valor;
        this.data = data;
        this.desconto = desconto;
        this.vendedorDoc = vendedorDoc;
        this.clienteDoc = clienteDoc;
    }
    
    public void atualizar(List<Cliente> c, List<Funcionario> v){
        for(Cliente cliente : c)
            if(cliente.getDocumento().equals(clienteDoc))
                this.cliente = cliente;
        for(Funcionario vendedor : v)
            if(vendedor.getDocumento().equals(vendedorDoc))
                this.vendedor = vendedor;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Funcionario getVendedor() {
        return vendedor;
    }

    public void setVendedor(Vendedor vendedor) {
        this.vendedor = vendedor;
    }

    public Cliente getCliente() {
        return cliente;
    }

    public void setCliente(Cliente cliente) {
        this.cliente = cliente;
    }

    public Veiculo getVeiculo() {
        return veiculo;
    }

    public void setVeiculo(Veiculo veiculo) {
        this.veiculo = veiculo;
    }

    public double getValor() {
        return valor;
    }

    public void setValor(double valor) {
        this.valor = valor;
    }

    public Data getData() {
        return data;
    }

    public void setData(Data data) {
        this.data = data;
    }

    public double getDesconto() {
        return desconto;
    }

    public void setDesconto(double desconto) {
        this.desconto = desconto;
    }
    
    
}
