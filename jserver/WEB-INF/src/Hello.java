package com.infortechn;

import java.io.*;
import java.util.Properties;
import javax.servlet.*;
import javax.servlet.http.*;

public class Hello extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws IOException, ServletException
    {
	response.setCharacterEncoding("UTF-8");
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
	String docRoot = getServletContext().getRealPath("./");
	Properties p = Utils.loadSettings(docRoot + "settings.ini");
	out.println(p.getProperty("host"));
    }
}
