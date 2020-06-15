FROM node:latest

ADD frontend/dist /dist

ADD frontend/server /server
RUN cd /server && yarn install

CMD ["node", "/server/server.js"]