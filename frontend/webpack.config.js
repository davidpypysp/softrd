const path = require("path");
const HtmlWebPackPlugin = require("html-webpack-plugin");

module.exports = {
    entry: "./src/index.tsx",
    resolve: {
        alias: {
            src: path.resolve(__dirname, "src/"),
            styles: path.resolve(__dirname, "styles/"),
        },
        extensions: [".tsx", ".ts", ".js"],
    },
    output: {
        filename: "bundle.js",
        path: path.resolve(__dirname, "dist"),
    },
    devtool: "cheap-source-map",
    node: {
        fs: "empty",
    },
    module: {
        rules: [
            {
                test: /\.(js|jsx|ts|tsx)$/,
                enforce: "pre",
                exclude: [/node_modules/],
                use: ["eslint-loader"],
            },
            {
                test: /\.ts(x?)$/,
                use: "ts-loader",
                exclude: /node_modules/,
            },
            {
                enforce: "pre",
                test: /\.js$/,
                loader: "source-map-loader",
            },
            {
                test: /\.html$/,
                use: [
                    {
                        loader: "html-loader",
                    },
                ],
            },
            {
                test: /\.css$/,
                use: ["style-loader", "css-loader"],
            },
            {
                test: /\.scss$/,
                use: [
                    {
                        loader: "style-loader",
                    },
                    {
                        loader: "css-loader",
                    },
                    {
                        loader: "sass-loader",
                    },
                ],
            },
            {
                test: /\.(woff(2)?|ttf|eot|svg)(\?v=\d+\.\d+\.\d+)?$/,
                use: [
                    {
                        loader: "file-loader",
                        options: {
                            name: "[name].[ext]",
                            outputPath: "fonts/",
                        },
                    },
                ],
            },
            {
                test: /\.wasm$/,
                type: "javascript/auto",
                use: [
                    {
                        loader: "file-loader",
                        options: {
                            name: "[name].[ext]",
                            outputPath: "wasm/",
                            publicPath: "wasm/",
                        },
                    },
                ],
            },
        ],
    },
    plugins: [
        new HtmlWebPackPlugin({
            template: "./src/index.ejs",
            filename: "./index.html",
        }),
    ],
    devServer: {
        contentBase: false,
        publicPath: "/",
        port: 9000,
    },
};
