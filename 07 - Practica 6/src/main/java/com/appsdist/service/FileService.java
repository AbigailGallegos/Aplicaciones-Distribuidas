package com.appsdist.service;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.core.io.ClassPathResource;
import org.springframework.stereotype.Service;
import org.thymeleaf.context.Context;
import org.thymeleaf.spring6.SpringTemplateEngine;
import org.thymeleaf.spring6.view.ThymeleafViewResolver;
import org.xhtmlrenderer.pdf.ITextRenderer;

import com.appsdist.model.Student;
import com.lowagie.text.DocumentException;

@Service
public class FileService {
	
	private static final String PDF_RESOURCES = "/pdf-resources/";
	
	private final SpringTemplateEngine templateEngine;
	
	@Autowired
	public FileService(SpringTemplateEngine templateEngine) {
		this.templateEngine = templateEngine;
	}
	
	public File geratedPdf() throws IOException, DocumentException {
		Context context = getContext();
        String html = loadAndFillTemplate(context);
        return renderPdf(html);
	}
	
	  private File renderPdf(String html) throws IOException, DocumentException {
	        File file = File.createTempFile("Estudiantes", ".pdf");
	        OutputStream outputStream = new FileOutputStream(file);
	        ITextRenderer renderer = new ITextRenderer(20f * 4f / 3f, 20);
	        renderer.setDocumentFromString(html, new ClassPathResource(PDF_RESOURCES).getURL().toExternalForm());
	        renderer.layout();
	        renderer.createPDF(outputStream);
	        outputStream.close();
	        file.deleteOnExit();
	        return file;
	    }

	    private Context getContext() {
	        Context context = new Context();
	        List<Student> estudiantes = new ArrayList();
	        Student student = new Student();
	        student.setId(1);
	        student.setName("Diana Abigail");
	        student.setLastName("Gallegos Ruiz");
	        student.setUniversity("IPN");
	        student.setNationality("Mexicana");
	        student.setActive(true);
	        estudiantes.add(student);
	        student = new Student();
	        student.setId(2);
	        student.setName("Diego");
			student.setUniversity("UNAM");
	        student.setLastName("Flores Chavarría");
	        student.setNationality("Mexicana");
	        student.setActive(true);
	        estudiantes.add(student);
	        student = new Student();
	        student.setId(3);
	        student.setName("Felix");
	        student.setLastName("Mata");
	        student.setUniversity("IPN");
	        student.setNationality("Mexicana");
	        student.setActive(true);
	        estudiantes.add(student);
	        context.setVariable("students", estudiantes);
	        return context;
	    }

	    private String loadAndFillTemplate(Context context) {
	        return templateEngine.process("pdf_estudiantes", context);
	    }

	@Bean
	public ThymeleafViewResolver thymeleafViewResolver() {
		ThymeleafViewResolver resolver = new ThymeleafViewResolver();
		resolver.setTemplateEngine(templateEngine);
		resolver.setCharacterEncoding("UTF-8");
		return resolver;
	}

	

}
