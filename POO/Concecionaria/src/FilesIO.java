
import java.io.*;
import java.util.*;

public class FilesIO<T> {
    
    private File arquivo;
    private final static String lineEnding = "\r\n"; // \r\n no windows \n no linux
    
    public FilesIO(String path){
        try{
            
            arquivo = new File(path);
            if(!arquivo.exists())
                arquivo.createNewFile();
        
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    
    public void write(String m){
        try{
            FileWriter fileWriter = new FileWriter(arquivo, true);
            fileWriter.append(m + lineEnding);
            fileWriter.close();
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    public List<String> load(){
        List<String> output = new ArrayList<String>();
        try{
            BufferedReader bReader = new BufferedReader(new FileReader(arquivo));
            String line;
            while((line = bReader.readLine()) != null)
                output.add(line);
            bReader.close();
        }catch(IOException e){
            e.printStackTrace();
        }
        return output;
    }
    
    public boolean write(List<T> data){
        boolean output = false;
        
        try{
            FileWriter fileWriter = new FileWriter(arquivo);
        
            if(data.isEmpty())
                return output;
            
            //Escreve o cabeçalho do arquivo
            if(data.get(0) instanceof Gerente)
                fileWriter.write("GERENTES" + lineEnding);
            else if(data.get(0) instanceof VendedorS)
                fileWriter.write("SENIORS" + lineEnding);
            else if(data.get(0) instanceof VendedorJr)
                fileWriter.write("JUNIORS" + lineEnding);
            else if(data.get(0) instanceof Cliente)
                fileWriter.write("CLIENTES" + lineEnding);
            else if(data.get(0) instanceof Carro)
                fileWriter.write("CARROS" + lineEnding);
            else if(data.get(0) instanceof Motocicleta)
                fileWriter.write("MOTOCICLETAS" + lineEnding);
            else if(data.get(0) instanceof VendaPrazo)
                fileWriter.write("VENDAS" + lineEnding);
            
            //Escreve os dados no arquivo
            for(T d : data){
                if(d instanceof Pessoa){
                    Pessoa pessoa = (Pessoa)d;
                    fileWriter.write(pessoa.getNome() + lineEnding);
                    fileWriter.write(pessoa.getDocumento() + lineEnding);
                    fileWriter.write(pessoa.getNasc().string() + lineEnding);
                    fileWriter.write(pessoa.getRenda() + lineEnding);
                    
                    if(pessoa instanceof Funcionario){
                        Funcionario funcionario = (Funcionario)pessoa;
                        fileWriter.write(funcionario.getUsuario() + lineEnding);
                        fileWriter.write(funcionario.getSenha() + lineEnding);
                        fileWriter.write(funcionario.getAdmissao().string() + lineEnding);
                        
                        if(funcionario instanceof VendedorJr){
                            VendedorJr vendedorJr = (VendedorJr)funcionario;
                            fileWriter.write(vendedorJr.getTempoTrabalho() + lineEnding);
                            fileWriter.write(vendedorJr.getGerenteResponsavel().getDocumento() + lineEnding);                            
                        }else if(funcionario instanceof VendedorS){
                            VendedorS vendedorS = (VendedorS)funcionario;
                            fileWriter.write(vendedorS.getAnosTrabalho() + lineEnding);
                        }
                        
                    }else{
                        Cliente cliente = (Cliente)pessoa;
                        fileWriter.write(cliente.getEndereco().string() + lineEnding);
                        fileWriter.write(cliente.getDependentes() + lineEnding);
                    }
                }
                else if(d instanceof Veiculo){
                    Veiculo veiculo = (Veiculo)d;
                    fileWriter.write(veiculo.getChassi() + lineEnding);
                    fileWriter.write(veiculo.getMarca() + lineEnding);
                    fileWriter.write(veiculo.getModelo() + lineEnding);
                    fileWriter.write(veiculo.getAno() + lineEnding);
                    fileWriter.write(veiculo.getKm() + lineEnding);
                    fileWriter.write(veiculo.getComb() + lineEnding);
                    fileWriter.write(veiculo.getPeso() + lineEnding);
                    fileWriter.write(veiculo.getStatus() + lineEnding);
                    if(veiculo instanceof Carro){
                        Carro carro = (Carro)veiculo;
                        fileWriter.write(carro.getPotencia() + lineEnding);
                        fileWriter.write(carro.getCilindros() + lineEnding);
                        fileWriter.write(carro.getOcupantes() + lineEnding);
                        fileWriter.write(carro.getTipo() + lineEnding);
                        fileWriter.write(carro.getDimensoes().string() + lineEnding);
                    }
                    if(veiculo instanceof Motocicleta){
                        Motocicleta moto = (Motocicleta)veiculo;
                        fileWriter.write(moto.getCilindradas() + lineEnding);
                        fileWriter.write(moto.getTipo() + lineEnding);
                    }
                }else if(d instanceof VendaPrazo){
                    VendaPrazo venda = (VendaPrazo)d;
                    fileWriter.write(venda.getId() + lineEnding);
                    fileWriter.write(venda.getVendedor().getDocumento()+ lineEnding);
                    fileWriter.write(venda.getCliente().getDocumento() + lineEnding);
                    //Salvando o veiculo
                    Veiculo veiculo = venda.getVeiculo();
                    //Antes uma linha pra saber o tipo do veiculo
                    if(veiculo instanceof Carro)
                        fileWriter.write("CARRO" + lineEnding);
                    else
                        fileWriter.write("MOTO" + lineEnding);
                    fileWriter.write(veiculo.getChassi() + lineEnding);
                    fileWriter.write(veiculo.getMarca() + lineEnding);
                    fileWriter.write(veiculo.getModelo() + lineEnding);
                    fileWriter.write(veiculo.getAno() + lineEnding);
                    fileWriter.write(veiculo.getKm() + lineEnding);
                    fileWriter.write(veiculo.getComb() + lineEnding);
                    fileWriter.write(veiculo.getPeso() + lineEnding);
                    fileWriter.write(veiculo.getStatus() + lineEnding);
                    if(veiculo instanceof Carro){
                        Carro carro = (Carro)veiculo;
                        fileWriter.write(carro.getPotencia() + lineEnding);
                        fileWriter.write(carro.getCilindros() + lineEnding);
                        fileWriter.write(carro.getOcupantes() + lineEnding);
                        fileWriter.write(carro.getTipo() + lineEnding);
                        fileWriter.write(carro.getDimensoes().string() + lineEnding);
                    }
                    if(veiculo instanceof Motocicleta){
                        Motocicleta moto = (Motocicleta)veiculo;
                        fileWriter.write(moto.getCilindradas() + lineEnding);
                        fileWriter.write(moto.getTipo() + lineEnding);
                    }
                    fileWriter.write(venda.getValor() + lineEnding);
                    fileWriter.write(venda.getData().string() + lineEnding);
                    fileWriter.write(venda.getDesconto() + lineEnding);
                    fileWriter.write(venda.getParcelas() + lineEnding);
                }
            }
            
            //Termina o arquivo
            fileWriter.close();
            output = true;
            
        }catch(IOException e){
            e.printStackTrace();
        }
        
        return output;
    }
    
    public List<T> read(){
        List<T> output = new ArrayList<T>();
        
        try{
        
            BufferedReader bReader = new BufferedReader(new FileReader(arquivo));
        
            int type = 0;
            
            switch(bReader.readLine()){
                case "GERENTES":
                    type = 0;
                    break;
                case "SENIORS":
                    type = 1;
                    break;
                case "JUNIORS":
                    type = 2;
                    break;
                case "CARROS":
                    type = 3;
                    break;
                case "MOTOCICLETAS":
                    type = 4;
                    break;
                case "CLIENTES":
                    type = 5;
                    break;
                case "VENDAS":
                    type = 6;
                    break;
            }
            
            String line, marca, modelo, comb, documento, senha, usuario;
            Data nascimento, admissao;
            int ano, chassi;
            double km, peso, renda;
            Veiculo.Status status;
            
            while((line = bReader.readLine()) != null){
                switch(type){
                    //Gerentes
                    case 0:
                        //Pessoa
                        documento = bReader.readLine();
                        nascimento = new Data(bReader.readLine());
                        renda = Double.parseDouble(bReader.readLine());
                        //Funcionario
                        usuario = bReader.readLine();
                        senha = bReader.readLine();
                        admissao = new Data(bReader.readLine());
                        
                        output.add((T) new Gerente(
                                usuario,
                                senha,
                                line,
                                documento,
                                nascimento,
                                admissao,
                                renda
                        ));
                        break;
                    //Vendedor Senior
                    case 1:
                        //Pessoa
                        documento = bReader.readLine();
                        nascimento = new Data(bReader.readLine());
                        renda = Double.parseDouble(bReader.readLine());
                        //Funcionario
                        usuario = bReader.readLine();
                        senha = bReader.readLine();
                        admissao = new Data(bReader.readLine());
                        //VendedorS
                        int anosTrabalho = Integer.parseInt(bReader.readLine());
                        
                        output.add((T) new VendedorS(
                                usuario,
                                senha,
                                anosTrabalho,
                                line,
                                documento,
                                nascimento,
                                admissao,
                                renda
                        ));
                        break;
                    //Vendedor Junior
                    case 2:
                        //Pessoa
                        documento = bReader.readLine();
                        nascimento = new Data(bReader.readLine());
                        renda = Double.parseDouble(bReader.readLine());
                        //Funcionario
                        usuario = bReader.readLine();
                        senha = bReader.readLine();
                        admissao = new Data(bReader.readLine());
                        //VendedorJr
                        int tempoTrabalho = Integer.parseInt(bReader.readLine());
                        String gerente = bReader.readLine();
                        
                        output.add((T)new VendedorJr(
                                line,
                                documento,
                                nascimento,
                                renda,
                                usuario,
                                senha,
                                admissao,
                                tempoTrabalho,
                                gerente
                        ));
                        
                        break;
                    //Carros
                    case 3:
                        int potencia, cilindros, ocupantes;
                        Carro.Tipo tipo;
                        String dimensoes;
                        
                        chassi = Integer.parseInt(line);
                        marca = bReader.readLine();
                        modelo = bReader.readLine();
                        ano = Integer.parseInt(bReader.readLine());
                        km = Double.parseDouble(bReader.readLine());
                        comb = bReader.readLine();
                        peso = Double.parseDouble(bReader.readLine());
                        status = Veiculo.parseStatus(bReader.readLine());
                        
                        potencia = Integer.parseInt(bReader.readLine());
                        cilindros = Integer.parseInt(bReader.readLine());
                        ocupantes = Integer.parseInt(bReader.readLine());
                        tipo = Carro.parseTipo(bReader.readLine());
                        dimensoes = bReader.readLine();
                        
                        output.add((T) new Carro(
                                chassi,
                                marca,
                                modelo,
                                ano,
                                km,
                                comb,
                                peso,
                                status,
                                potencia,
                                cilindros,
                                ocupantes,
                                tipo,
                                new Dim(dimensoes)
                        ));
                        break;
                    //Motos
                    case 4:
                        int cilindradas;
                        Motocicleta.Tipo tipoM;
                        
                        chassi = Integer.parseInt(line);
                        marca = bReader.readLine();
                        modelo = bReader.readLine();
                        ano = Integer.parseInt(bReader.readLine());
                        km = Double.parseDouble(bReader.readLine());
                        comb = bReader.readLine();
                        peso = Double.parseDouble(bReader.readLine());
                        status = Veiculo.parseStatus(bReader.readLine());
                        
                        cilindradas = Integer.parseInt(bReader.readLine());
                        tipoM = Motocicleta.parseTipo(bReader.readLine());
                        
                        output.add((T) new Motocicleta(
                                chassi,
                                marca,
                                modelo,
                                ano,
                                km,
                                comb,
                                peso,
                                status,
                                cilindradas,
                                tipoM
                        ));
                        break;
                    //Clientes
                    case 5:
                        //Pessoa
                        documento = bReader.readLine();
                        nascimento = new Data(bReader.readLine());
                        renda = Double.parseDouble(bReader.readLine());
                        //Cliente
                        Endereco endereco = new Endereco(bReader.readLine());
                        int dependentes = Integer.parseInt(bReader.readLine());
                        
                        output.add((T)new Cliente(
                                line,
                                documento,
                                nascimento,
                                renda,
                                endereco,
                                dependentes
                        ));
                        break;
                    //Vendas
                    case 6:
                        //Line = id
                        String vendedorDocumento, clienteDocumento, dataDaVenda;
                        double valor, desconto;
                        int parcelas;
                        vendedorDocumento = bReader.readLine();
                        clienteDocumento = bReader.readLine();
                        Veiculo veiculo;
                        switch(bReader.readLine()){
                            case "CARRO":
                                int potenciaV, cilindrosV, ocupantesV;
                                Carro.Tipo tipoV;
                                String dimensoesV;
                        
                                chassi = Integer.parseInt(bReader.readLine());
                                marca = bReader.readLine();
                                modelo = bReader.readLine();
                                ano = Integer.parseInt(bReader.readLine());
                                km = Double.parseDouble(bReader.readLine());
                                comb = bReader.readLine();
                                peso = Double.parseDouble(bReader.readLine());
                                status = Veiculo.parseStatus(bReader.readLine());
                        
                                potenciaV = Integer.parseInt(bReader.readLine());
                                cilindrosV = Integer.parseInt(bReader.readLine());
                                ocupantesV = Integer.parseInt(bReader.readLine());
                                tipoV = Carro.parseTipo(bReader.readLine());
                                dimensoesV = bReader.readLine();
                        
                                veiculo =  new Carro(
                                    chassi,
                                    marca,
                                    modelo,
                                    ano,
                                    km,
                                    comb,
                                    peso,
                                    status,
                                    potenciaV,
                                    cilindrosV,
                                    ocupantesV,
                                    tipoV,
                                    new Dim(dimensoesV)
                                );
                                break;
                            default:
                                int cilindradasV;
                                Motocicleta.Tipo tipoMV;
                        
                                chassi = Integer.parseInt(bReader.readLine());
                                marca = bReader.readLine();
                                modelo = bReader.readLine();
                                ano = Integer.parseInt(bReader.readLine());
                                km = Double.parseDouble(bReader.readLine());
                                comb = bReader.readLine();
                                peso = Double.parseDouble(bReader.readLine());
                                status = Veiculo.parseStatus(bReader.readLine());
                        
                                cilindradasV = Integer.parseInt(bReader.readLine());
                                tipoMV = Motocicleta.parseTipo(bReader.readLine());
                        
                                veiculo = new Motocicleta(
                                    chassi,
                                    marca,
                                    modelo,
                                    ano,
                                    km,
                                    comb,
                                    peso,
                                    status,
                                    cilindradasV,
                                    tipoMV
                                );
                                
                                break;
                        }
                        valor = Double.parseDouble(bReader.readLine());
                        dataDaVenda = bReader.readLine();
                        desconto = Double.parseDouble(bReader.readLine());
                        parcelas = Integer.parseInt(bReader.readLine());
                        
                        output.add((T) new VendaPrazo(
                                parcelas,
                                Integer.parseInt(line),
                                veiculo,
                                valor,
                                new Data(dataDaVenda),
                                desconto,
                                vendedorDocumento,
                                clienteDocumento
                        ));
                        break;
                }
            }
            bReader.close();
        
        }catch(IOException e){
            e.printStackTrace();
        }
        
        return output;
    }
    
}
