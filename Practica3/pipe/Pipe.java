import java.io.*;
import java.net.*;

public class Pipe {
    
    public static void main(String[] args) {
        // Verificamos que se haya proporcionado el ID del proceso como argumento de línea de comandos
        if (args.length != 1) {
            System.out.println("Uso: java Pipe <ID_Proceso>");
            return;
        }
        
        // Parseamos el ID del proceso a partir del argumento de línea de comandos
        int ID_Proceso = Integer.parseInt(args[0]);
        int totalProcess = 3; // Número total de procesos 
        
        // Definimos el número de puerto base para la comunicación
        int PUERTO = 5000;
        int ID_puerto = PUERTO + ID_Proceso;
        int siguienteID = (ID_Proceso + 1) % totalProcess;
        int siguientePuerto = PUERTO + siguienteID;
        
         // Generamos un mensaje inicial aleatorio para este proceso
        int mensaje = (int) (Math.random() * 50 + 1);
        int suma = mensaje;
       
        try (ServerSocket serverSocket = new ServerSocket(ID_puerto)) {
            // Esperar un tiempo antes de comenzar
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                System.out.println("Se interrumpió el sueño del hilo");
            }
            
            System.out.println("Soy el Proceso (ID): " + ID_Proceso + " Mi número aleatorio: " + mensaje);
            
            // Creamos un socket de cliente para enviar el mensaje al proceso siguiente
             try (Socket clientSocket = new Socket("localhost", siguientePuerto)){
                
                // Enviar el mensaje al proceso siguiente 
                PrintWriter output = new PrintWriter(clientSocket.getOutputStream(), true);
           
                
                //Esperar la respuesta del proceso anterior         
                Socket clienteSocket = serverSocket.accept();
                BufferedReader input = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
           
                for (int i = 0; i < totalProcess - 1; i++) {
                 output.println(mensaje);
                 int recibido = Integer.parseInt(input.readLine());
                     
                 suma += recibido;
                 mensaje = recibido;
                 System.out.println("El Proceso (ID): " + ID_Proceso + " Recibo el valor: " + recibido);
                }
               
            }
 
            System.out.println("Soy el Proceso (ID): " + ID_Proceso + " Mi suma Global es: " + suma); 
        } catch (IOException e) {
            e.printStackTrace();
        }
        
    }// Main   
    
}//Pipe
