FROM node:13.7.0-alpine3.10
WORKDIR /usr/src/view
COPY . .
RUN npm i
RUN npm i typescript@3.4.5 -g
RUN npm i serve -g
RUN tsc
CMD ["serve"]
