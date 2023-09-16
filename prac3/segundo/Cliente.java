import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Cliente {

	final String HOST = "localhost";
	final int PUERTO = 4002;
	Socket sc;
	PrintWriter mensaje;
	BufferedReader entrada;
	String mensajeRecibido;
	Scanner teclado;
	List<String> Clientes = new ArrayList<String>();
	
	//Cliente
	public void initCliente(String nick) {
		try {
			sc = new Socket(HOST, PUERTO);
			mensaje = new PrintWriter(sc.getOutputStream(), true);
			entrada = new BufferedReader(new InputStreamReader(sc.getInputStream()));
			teclado = new Scanner(System.in);
			String continuar = "s"; //Utilizaremos un ciclo para seguir realizando operaciones
			int opcion;
			System.out.println(nick+ " esta iniciando conexion con el servidor...");
			//enviamos el mensaje 
			mensaje.println(nick);
			String valida;
			mensajeRecibido = entrada.readLine();
			valida = mensajeRecibido;
			while(valida.equals("n")) {
				System.out.println("Ingrese nuevo usuario:");
				mensaje.println(teclado.nextLine());
				mensajeRecibido = entrada.readLine();
				valida = mensajeRecibido;
			}
			/**
			 * Recopila los datos para llevarlos al servidor y que
			 * realice las operaciones.
			 */
				System.out.println("Calculadora de cliente\n "
						+ "Que operacion desea realizar?\n1) Sumar n numeros\n2) Multiplicar n numeros\n"
						+ "3) Restar dos numeros\n4) Dividir dos numeros\n5) Salir");
				opcion = teclado.nextInt();
				mensaje.println(String.valueOf(opcion));
					switch(opcion) {
					case 1:
						System.out.println("Operacion: Suma de n numeros.");
						//mensaje.println(nick+ "Quiere hacer una suma de numeros");
						int tamS, res;
						System.out.print("Cuantos numeros desea sumar? ");
						tamS = teclado.nextInt();
						mensaje.println(String.valueOf(tamS));
						for(int i = 0; i < tamS; i++) {
							System.out.println("Inserte el " +(i+1)+ " numero:");
							mensaje.println(String.valueOf(teclado.nextInt()));
						}
						res = Integer.parseInt(entrada.readLine());
						System.out.println("El resultado de la suma es: " +res);
						break;
					case 2:
						System.out.println("Operacion: Multiplicacion de n numeros.");
						//mensaje.println(nick+ "Quiere hacer una suma de numeros");
						int tamM, resM;
						System.out.print("Cuantos numeros desea multiplicar? ");
						tamM = teclado.nextInt();
						mensaje.println(String.valueOf(tamM));
						for(int i = 0; i < tamM; i++) {
							System.out.println("Inserte el " +(i+1)+ " numero:");
							mensaje.println(String.valueOf(teclado.nextInt()));
						}
						resM = Integer.parseInt(entrada.readLine());
						System.out.println("El resultado de la multiplicacion es: " +resM);
						break;
					case 3:
						System.out.println("Operacion: Resta de dos numeros.");
						int num1, num2, resResta;
						System.out.print("Ingrese el primer numero:");
						num1 = teclado.nextInt();
						mensaje.println(String.valueOf(num1));
						System.out.print("Ingrese el segundo numero:");
						num2 = teclado.nextInt();
						mensaje.println(String.valueOf(num2));
						mensajeRecibido = entrada.readLine();
						resResta = Integer.parseInt(mensajeRecibido);
						System.out.println("El resultado de la resta es: " +resResta);
						break;
					case 4:
						System.out.println("Operacion: Division de dos numeros.");
						int d1, d2, resDiv;
						System.out.print("Ingrese el primer numero:");
						d1 = teclado.nextInt();
						mensaje.println(String.valueOf(d1));
						System.out.print("Ingrese el segundo numero:");
						d2 = teclado.nextInt();
						while(d2 == 0) {
							System.out.println("No se puede dividir entre 0! inserte un numero distinto.");
							d2 = teclado.nextInt();
						}
						mensaje.println(String.valueOf(d2));
						mensajeRecibido = entrada.readLine();
						resDiv = Integer.parseInt(mensajeRecibido);
						System.out.println("El resultado de la division es: " +resDiv);
						break;
					case 5:
						mensaje.println(nick+ "Sale de la calculadora");
						continuar = "n";
						break;
					}
					/*System.out.println("Desea continuar haciendo operaciones? (s/n)");
					continuar = teclado.nextLine();
					if(continuar.equals("n")) {
						opcion = 5;
						mensaje.println(String.valueOf(opcion));
					}*/

			//Cerramos la conexion
			teclado.close();
			sc.close();
		}catch(IOException e) {
			System.out.println("Error: " +e.getMessage());
		}
	}
	

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String nickname;
		Scanner ent = new Scanner(System.in);
		System.out.println("Bienvenido a la calculadora, por favor ingrese su nickname:");
		nickname = ent.nextLine();
		Cliente c = new Cliente();
		c.initCliente(nickname);
	}

}