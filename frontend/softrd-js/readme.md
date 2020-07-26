# softrd-js

Javascript version of softrd renderer API.

Upload process:
```
    modify package.json "version" to be higher.
    npm publish --access public
```

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