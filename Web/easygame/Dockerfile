# Origin image
FROM lanceaking/lamp

# Meta Information
MAINTAINER Donek1 "donek1@qq.com"
	
## delete index
RUN rm /var/www/html/index.html
	
## Copy code
ADD src/* /var/www/html/
	
## port
EXPOSE 80
