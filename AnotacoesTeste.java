import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

// Cria uma anotação visível em tempo de execução
@Retention(RetentionPolicy.RUNTIME)
@interface MinhaAnotacao {
    String valor() default "teste";
}

public class AnotacoesTeste {
    @MinhaAnotacao(valor = "Implementado")
    public int campoComAnotacao;
    
    @Deprecated
    public String campoObsoleto;
}