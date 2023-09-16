import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.Scanner;;

public class ServidorMultiHilado implements Runnable{

	static final int PUERTO = 4002;
	Socket s;
	static ArrayList<String> usuarios = new ArrayList<String>();
	
	public ServidorMultiHilado() {
		initServidor();
	}
	
	public ServidorMultiHilado(Socket s) {
		this.s = s;
	}

	//Servidor
	public void initServidor() {
		ServerSocket sc;
		Socket so;
		
		try {
			sc = new ServerSocket(PUERTO);
			while(true) {
				System.out.println("Esperando una conexion...");
				so = sc.accept();
				ServidorMultiHilado hilo = new ServidorMultiHilado(so);
				Thread hiloCliente = new Thread(hilo);
				hiloCliente.start();
				/*
				 * Inicia el socket, ahora espera una conexion
				 * por parte del cliente
				 */
				System.out.println("Un cliente se ha conectado!");
			}
		}catch(Exception e) {
			System.out.println("Error: " +e.getMessage());
		}
	}

	//Objetos que van a tener lecuras y escrituras
	@Override
	public void run() {
		// TODO Auto-generated method stub
		PrintWriter salida = null;
		String mensajeRecibido = "";
		BufferedReader entrada = null;
		try {
			entrada = new BufferedReader(new InputStreamReader(s.getInputStream()));
		}catch(IOException e3) {
			e3.printStackTrace();
		}
		try {
			salida = new PrintWriter(s.getOutputStream(), true);
		}catch(IOException e2) {
			e2.printStackTrace();
		}
		System.out.println("Confirmando conexion al cliente...");
		//salida.println("Conexion exitosa, bienvenido!");
		try {
			mensajeRecibido = entrada.readLine();
		}catch(IOException e1) {
			e1.printStackTrace();
		}
		String cliente = mensajeRecibido;
		String validacion = "n";
		do {
			if(usuarios.contains(cliente)) {
				System.out.println("El usuario ya existe, favor de ingresar otro.");
				validacion = "n";
				salida.println(validacion);
				try {
					mensajeRecibido = entrada.readLine();
					cliente = mensajeRecibido;
				}catch(IOException e1) {
					e1.printStackTrace();
				}
			}else {
				usuarios.add(cliente);
				validacion = "y";
				salida.println(validacion);
			}
		}while(validacion.equals("n"));
		
		System.out.println("bienvenido! " +mensajeRecibido);
		//Preparar la calculadora para realizar las operaciones
		try {
			mensajeRecibido = entrada.readLine();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		System.out.println("Seleccionada la opcion: " +mensajeRecibido);
		int opcCalc = Integer.parseInt(mensajeRecibido);
		//System.out.println("Esperando instrucciones del cliente...");
		//while(opcCalc != 5) {
			switch(opcCalc) {
			case 1:
				int tamSuma = 0;
				int sumaT = 0;
				System.out.println("El cliente " +cliente+ " ha seleccionado la suma");
				try {
					mensajeRecibido = entrada.readLine();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				tamSuma = Integer.parseInt(mensajeRecibido);
				System.out.println("Total de numeros a sumar:" +tamSuma);
				for(int i = 1; i <= tamSuma; i++) {
					try {
						mensajeRecibido = entrada.readLine();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					sumaT += Integer.parseInt(mensajeRecibido);
				}
				//System.out.println("La suma es: " +sumaT);
				salida.println(sumaT);
				break;
			case 2:
				int tamMult= 0;
				int MultT = 1;
				System.out.println("El cliente " +cliente+ " ha seleccionado la multiplicacion");
				try {
					mensajeRecibido = entrada.readLine();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				tamMult = Integer.parseInt(mensajeRecibido);
				System.out.println("Total de numeros a multiplicar:" +tamMult);
				for(int i = 1; i <= tamMult; i++) {
					try {
						mensajeRecibido = entrada.readLine();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					MultT = MultT * Integer.parseInt(mensajeRecibido);
				}
				//System.out.println("La suma es: " +sumaT);
				salida.println(MultT);
				break;
			case 3:
				System.out.println("El cliente " +cliente+ " ha seleccionado la resta");
				int v1, v2, resR;
				try {
					mensajeRecibido = entrada.readLine();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				v1 = Integer.parseInt(mensajeRecibido);
				System.out.println("Numero 1 almacenado:" +v1);
				try {
					mensajeRecibido = entrada.readLine();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				v2 = Integer.parseInt(mensajeRecibido);
				System.out.println("Numero 2 almacenado: " +v2);
				resR = v1 - v2;
				salida.println(resR);
				break;
			case 4:
				System.out.println("El cliente " +cliente+ " ha seleccionado la division");
				int d1, d2, resDiv;
				try {
					mensajeRecibido = entrada.readLine();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				d1 = Integer.parseInt(mensajeRecibido);
				System.out.println("Numero 1 almacenado:" +d1);
				try {
					mensajeRecibido = entrada.readLine();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				d2 = Integer.parseInt(mensajeRecibido);
				System.out.println("Numero 2 almacenado: " +d2);
				resDiv = d1 / d2;
				salida.println(resDiv);
				break;
			case 5:
				System.out.println("El cliente " +cliente+ " no hizo ninguna operacion...");
				opcCalc = 5;
				break;
			default:
				opcCalc = 5;
				break;
			}
			opcCalc = 5;
			
		//}
		System.out.println("Cerrando Conexion. Gracias " +cliente+ " por usar la calculadora!");
		usuarios.remove(cliente);
		try {
			s.close();
		}catch(IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ServidorMultiHilado s = new ServidorMultiHilado();
	}

}