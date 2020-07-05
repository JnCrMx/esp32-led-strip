import React from 'react';
import IroColorPicker from './IroColorPicker.js';
import iro from '@jaames/iro';
import colorsys from 'colorsys';
import axios from 'axios';
import './App.css';

class App extends React.Component
{
	state = {
		color: {
		},
		brightness: 100,
		size: 0
	}

	handleColorChange = (picker) =>
	{
		this.setState({color: picker.$}, this.update);
	}

	handleBrightness = (event) =>
	{
		const value = event.target.value;
		this.setState({brightness: value}, this.update);
	}

	handleResize = () =>
	{
		this.setState({ size: Math.min(window.innerWidth, window.innerHeight) * 0.90 });
	}

	update = () =>
	{
		var color = {...this.state.color};
		color.v = this.state.brightness;
		color = colorsys.hsv_to_rgb(color);

		axios.post('/api/color', color).catch(err => {
			window.alert(err);
		});
	}

	componentDidMount()
	{
		this.handleResize();
		window.addEventListener('resize', this.handleResize);

		axios.get('/api/color').then(res => {
			var hsvColor = colorsys.rgb_to_hsv(res.data);
			this.setState({color: hsvColor, brightness: hsvColor.v});
		}).catch(err => {
			window.alert(err);
		});
	}

	componentWillUnmount()
	{
		window.removeEventListener('resize', this.handleResize);
	}

	render()
	{
		var color = {...this.state.color};
		color.v = 100;
		var colorRGB = colorsys.hsv_to_rgb(color);

		var colorAdj = {...this.state.color};
		colorAdj.v = this.state.brightness;
		var colorAdjRGB = colorsys.hsv_to_rgb(colorAdj);

		var sliderStyle = {
			background: 'linear-gradient(90deg, rgba(0,0,0,1) 0%, ' + colorsys.stringify(colorRGB) + ' 100%)'
		}
		sliderStyle['--sliderThumb']=colorsys.stringify({r: 255-colorAdjRGB.r, g: 255-colorAdjRGB.g, b: 255-colorAdjRGB.b});

		return (
			<div className="App" style={{backgroundColor: colorsys.stringify(colorAdjRGB)}}>
				<IroColorPicker layout={[{component: iro.ui.Wheel}]} width={this.state.size} color={color} onColorChange={this.handleColorChange}/>
				<input type="range" min="0" max="99" value={this.state.brightness} className="slider" onChange={this.handleBrightness} style={sliderStyle}/>
			</div>
		);
	}
}

export default App;
