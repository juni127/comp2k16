public class VendaPrazo extends Vendas{
    private int parcelas;

    public VendaPrazo(int parcelas, int id, Vendedor vendedor, Cliente cliente, Veiculo veiculo, double valor, Data data, double desconto) {
        super(id, vendedor, cliente, veiculo, valor, data, desconto);
        this.parcelas = parcelas;
    }
    
    public VendaPrazo(int parcelas, int id, Veiculo veiculo, double valor, Data data, double desconto, String vendedorDoc, String clienteDoc){
        super(id, veiculo, valor, data, desconto, vendedorDoc, clienteDoc);
        this.parcelas = parcelas;
    }

    public int getParcelas() {
        return parcelas;
    }
    /*
    Não sei se interessa um método desse tipo, essa parte de venda é quite tricky
    public void divideValor(){
        valor = valor/parcelas;
    }
    */
    
}
