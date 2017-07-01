/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Reinaldo
 */
public class Funcionario extends Pessoa{
    
    private String usuario, senha;
    
    public Funcionario(String usuario, String senha){
        this.usuario = usuario;
        this.senha = senha;
    }
    
    public String getUsuario(){
        return this.usuario;
    }
    
    public String getSenha(){
        return this.senha;
    }
    
    public void setUsuario(String usuario){
        this.usuario = usuario;
    }
    
    public void setSenha(String senha){
        this.senha = senha;
    }
    
}
