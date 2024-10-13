from http.server import BaseHTTPRequestHandler, HTTPServer
import webbrowser

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/open':
            # URL to open
            url = 'https://www.youtube.com/watch?v=F6wtnzyFr78'  # Replace with the link you want to open
            webbrowser.open(url)
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(b'Link opened')
        else:
            self.send_response(404)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(b'Not Found')

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting server on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()
