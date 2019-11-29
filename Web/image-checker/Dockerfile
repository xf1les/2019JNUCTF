FROM lanceaking/lamp

RUN rm -rf /var/www/html
COPY html /var/www/html

COPY apache2.conf /etc/apache2/apache2.conf

RUN chgrp -R www-data /var/www/html
WORKDIR /var/www/html

RUN chmod g+w uploads

COPY flag /flag
