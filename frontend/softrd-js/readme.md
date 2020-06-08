# softrd-js

Javascript version of softrd renderer API.

Need to add this rule to webpack.config.js module.rules for loading wasm file
```
    {
        test: /\.wasm$/,
        type: 'javascript/auto',
        use: [
            {
                loader: 'file-loader',
                options: {
                    name: '[name].[ext]',
                    outputPath: 'wasm/',
                    publicPath: 'wasm/'
                }
            }
        ]
    }
```