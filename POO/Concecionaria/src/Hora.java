package Sistema;

import java.util.*;
import java.io.*;
import java.text.*;

public class Hora
{
	private int hora;
	private int min;
	
	public void setHora()
	{
		GregorianCalendar calendar = new GregorianCalendar();
		this.hora = calendar.get(Calendar.HOUR_OF_DAY);
		this.min = calendar.get(Calendar.MINUTE);
	}
	
	public int getHora()
	{
		return this.hora;
	}
	
	public int getMin()
	{
		return this.min;
	}
}