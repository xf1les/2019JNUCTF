FROM lanceaking/lamp
RUN rm /var/www/html/index.html
COPY src/* /var/www/html/
COPY flag /flag

RUN chmod 777 /var/www/html/youcantfind &&\
    chmod 777 /var/www/html &&\
    chmod 755 /var/www/html/flag.php &&\
    chmod 755 /var/www/html/index.php &&\
    chmod 755 /var/www/html/youcantfind/d0cb52940652171fc01a7639aa7285537f13ad97.php &&\
    chmod 755 /flag &&\
    chmod 755 /var/www/html/sssssource.txt


COPY rmupload /etc/periodic/15min/rmupload
RUN chmod 755 /etc/periodic/15min/rmupload

EXPOSE 80

